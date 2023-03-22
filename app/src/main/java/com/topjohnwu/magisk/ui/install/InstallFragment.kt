package com.topjohnwu.magisk.ui.install

import com.topjohnwu.magisk.R
import com.topjohnwu.magisk.arch.BaseFragment
import com.topjohnwu.magisk.arch.viewModel
import com.topjohnwu.magisk.databinding.FragmentInstallBinding

class InstallFragment : BaseFragment<FragmentInstallBinding>() {

    override val layoutRes = R.layout.fragment_install
    override val viewModel by viewModel<InstallViewModel>()

    override fun onStart() {
        super.onStart()
        requireActivity().setTitle(R.string.install)
    }
}
